#!/usr/bin/env bash
#
# フォーマット: clang-format でコードスタイルを揃える。
#
# 42 CPP はスタイル強制なしのため、これは採点要件ではなく
# 「自分が読みやすく開発するため」の任意整備。ベーススタイルは .clang-format（LLVM）。
#
# 使い方:
#   scripts/format.sh [--check] [path...]
#     - 既定（pre-commit 用）: clang-format -i で対象を整形する。
#     - --check（CI 用）: 整形差分があれば非ゼロで終了する（ファイルは変更しない）。
#     - path を渡さなければステージ済みの C++ ファイルを対象にする。

set -euo pipefail

check_only=0
if [ "${1:-}" = "--check" ]; then
	check_only=1
	shift
fi

# 対象ファイル一覧。
if [ "$#" -gt 0 ]; then
	files=("$@")
else
	mapfile -t files < <(git diff --cached --name-only --diff-filter=ACMR)
fi

# C++ ソース/ヘッダだけに絞る。
sources=()
for f in "${files[@]}"; do
	case "$f" in
		*.cpp | *.hpp | *.tpp | *.h)
			[ -f "$f" ] && sources+=("$f")
			;;
	esac
done

if [ "${#sources[@]}" -eq 0 ]; then
	exit 0
fi

if [ "$check_only" -eq 1 ]; then
	# CI 用: 整形が必要なら弾く（ファイルは変更しない）。
	clang-format --dry-run --Werror "${sources[@]}"
else
	# pre-commit 用: その場で整形する。再 stage は lefthook の stage_fixed に任せる。
	clang-format -i "${sources[@]}"
fi
