#!/usr/bin/env bash
#
# 静的解析リント: cppcheck と clang-tidy で、コンパイラ（-Wall -Wextra）が
# 見逃すバグ（メモリリーク・未初期化メンバ・delete/delete[] の取り違え等）を検出する。
#
# CPP の山場はメモリ管理と Orthodox Canonical Form であり、そこのミスは採点にも
# 学習にも直結する。pre-commit で必須チェックとして弾く。
#
# 対象は差分のあった C++ ファイルだけに絞り、速度を保つ。
#
# 使い方:
#   scripts/lint.sh [path...]
#     - 引数で対象ファイルを渡せる（lefthook の {staged_files} 用）。
#     - 引数が無ければステージ済みファイルを対象にする。
#
# 設定:
#   - cppcheck: c++98 / 重要度 warning 以上で検出。
#   - clang-tidy: .clang-tidy の設定に従う（modernize-* は c++98 と衝突するため無効）。

set -euo pipefail

# 42 の採点に合わせた C++ 標準。clang-tidy のコンパイル引数にも渡す。
CXXSTD="c++98"

# 対象ファイル一覧。
if [ "$#" -gt 0 ]; then
	files=("$@")
else
	mapfile -t files < <(git diff --cached --name-only --diff-filter=ACMR)
fi

# cppcheck/clang-tidy はソース(.cpp)を起点に解析する。ヘッダは include 経由で見られる。
sources=()
for f in "${files[@]}"; do
	case "$f" in
		*.cpp)
			[ -f "$f" ] && sources+=("$f")
			;;
	esac
done

if [ "${#sources[@]}" -eq 0 ]; then
	exit 0
fi

status=0

echo "▶ cppcheck"
# --error-exitcode=1 で指摘があれば非ゼロ終了させてブロックする。
# --inline-suppr で必要時にコード側 suppress を許可する。
if ! cppcheck \
	--std="$CXXSTD" \
	--enable=warning,performance,portability \
	--inline-suppr \
	--error-exitcode=1 \
	--quiet \
	"${sources[@]}"; then
	echo "✖ cppcheck が問題を検出しました。" >&2
	status=1
fi

echo "▶ clang-tidy"
# clang-tidy はコンパイルDBが無いので "--" 以降にコンパイル引数を渡す。
# Nix の devShell では標準ヘッダ（libc++ / clang builtin / SDK）の場所が
# 通常の場所と違うため、環境から導出して明示的に渡す。値が取れない環境
# （素の Linux など）では空のまま渡し、ツール既定の探索に委ねる。
tidy_args=(-std="$CXXSTD" -Wall -Wextra)

# libc++ の include（.../include/c++/v1）を NIX_CFLAGS_COMPILE から拾う。
if [ -n "${NIX_CFLAGS_COMPILE:-}" ]; then
	libcxx_dev="$(printf '%s\n' $NIX_CFLAGS_COMPILE | grep -m1 'libcxx.*-dev/include' || true)"
	if [ -n "$libcxx_dev" ] && [ -d "$libcxx_dev/c++/v1" ]; then
		tidy_args+=(-stdlib=libc++ -isystem "$libcxx_dev/c++/v1")
	fi
fi

# clang builtin ヘッダ（stdarg.h 等）の場所。
if resource_dir="$(clang -print-resource-dir 2>/dev/null)" && [ -n "$resource_dir" ]; then
	tidy_args+=(-resource-dir "$resource_dir")
fi

# macOS SDK の sysroot。
if [ -n "${SDKROOT:-}" ]; then
	tidy_args+=(-isysroot "$SDKROOT")
fi

if ! clang-tidy "${sources[@]}" -- "${tidy_args[@]}"; then
	echo "✖ clang-tidy が問題を検出しました。" >&2
	status=1
fi

if [ "$status" -ne 0 ]; then
	echo >&2
	echo "✖ リントで問題が検出されました。修正してから再コミットしてください。" >&2
fi

exit "$status"
