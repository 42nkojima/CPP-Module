#!/usr/bin/env bash
#
# ビルドチェック: 差分のあった cppNN/exNN/ を 42 の採点フラグでビルドする。
#
# 42 の採点はコンパイル必須（-Wall -Wextra -Werror、-std=c++98 でも通ること）。
# 壊れたコードをコミットしないよう、コミット前に弾く。
#
# 対象は「ステージされたファイルが属する cppNN/exNN/ ディレクトリ」だけに絞り、
# 全モジュールを毎回ビルドして遅くなるのを避ける。
#
# 使い方:
#   scripts/check-build.sh [path...]
#     - 引数で対象ファイルを渡せる（lefthook の {staged_files} 用）。
#     - 引数が無ければ、ステージ済みファイル（git diff --cached）を対象にする。
#
# Makefile があれば make、無ければ exNN 配下の *.cpp を直接コンパイルする。

set -euo pipefail

# 42 の採点に合わせたコンパイラとフラグ。Makefile が無い ex の直接ビルドにも使う。
CXX="${CXX:-c++}"
CXXFLAGS="-Wall -Wextra -Werror -std=c++98"

# 対象ファイル一覧を取得する。
if [ "$#" -gt 0 ]; then
	files=("$@")
else
	# ステージ済み（Added/Copied/Modified/Renamed）のファイルのみ。
	mapfile -t files < <(git diff --cached --name-only --diff-filter=ACMR)
fi

# ファイルパスから cppNN/exNN ディレクトリを抽出して一意化する。
modules=()
for f in "${files[@]}"; do
	# 例: cpp00/ex01/main.cpp -> cpp00/ex01
	if [[ "$f" =~ ^(cpp[0-9]{2}/ex[0-9]{2})/ ]]; then
		modules+=("${BASH_REMATCH[1]}")
	fi
done

if [ "${#modules[@]}" -eq 0 ]; then
	# 対象の演習ディレクトリに差分なし。何もせず通す。
	exit 0
fi

# 重複を除去する。
mapfile -t modules < <(printf '%s\n' "${modules[@]}" | sort -u)

status=0
for dir in "${modules[@]}"; do
	if [ ! -d "$dir" ]; then
		# ディレクトリごと削除された差分などはスキップ。
		continue
	fi

	echo "▶ build: $dir"
	if [ -f "$dir/Makefile" ]; then
		# Makefile があれば素の make に任せる（提出物と同じ経路）。
		if ! make -C "$dir"; then
			echo "✖ build failed: $dir (make)" >&2
			status=1
		fi
	else
		# Makefile が無ければ exNN 配下の *.cpp を直接コンパイルして確認する。
		mapfile -t sources < <(find "$dir" -maxdepth 1 -name '*.cpp')
		if [ "${#sources[@]}" -eq 0 ]; then
			echo "  (no .cpp / Makefile; skip)"
			continue
		fi
		# shellcheck disable=SC2086
		if ! "$CXX" $CXXFLAGS "${sources[@]}" -o /dev/null; then
			echo "✖ build failed: $dir ($CXX $CXXFLAGS)" >&2
			status=1
		fi
	fi
done

if [ "$status" -ne 0 ]; then
	echo >&2
	echo "✖ ビルドに失敗したモジュールがあります。修正してから再コミットしてください。" >&2
fi

exit "$status"
