#!/usr/bin/env bash
#
# 禁止事項チェック: 課題の禁止事項を grep で検出して弾く。
#
# 42 CPP には「使うと 0 点 / -42」になる禁止事項がある（subject より）:
#   - using namespace <ns> / friend           → -42
#   - *printf / *alloc / free                  → 0 点
#   - STL のコンテナ・アルゴリズム             → Module 08・09 以外は禁止（-42）
#
# モジュール番号によって STL の可否が変わる（08/09 のみ可）点を考慮する。
#
# 使い方:
#   scripts/check-forbidden.sh [path...]
#     - 引数で対象ファイルを渡せる（lefthook の {staged_files} 用）。
#     - 引数が無ければステージ済みファイルを対象にする。
#
# 注意: コメントや文字列リテラル内も素朴に grep で拾う。誤検出が問題になったら精緻化する。

set -euo pipefail

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

# どのモジュールでも禁止のパターン（説明文付き）。
# 形式: "正規表現<TAB>説明"
always_forbidden=(
	'using[[:space:]]+namespace[[:space:]]	using namespace（-42）'
	'\bfriend\b	friend（-42）'
	'\b[a-z_]*printf[[:space:]]*\(	*printf 系（0 点）'
	'\b(m|c|re)alloc[[:space:]]*\(	*alloc 系（0 点）'
	'\bfree[[:space:]]*\(	free（0 点）'
)

# STL（Module 08/09 以外で禁止）の検出パターン。
# コンテナ/アルゴリズムのヘッダ include と、std:: 直接利用の両方を素朴に拾う。
stl_forbidden=(
	'#[[:space:]]*include[[:space:]]*<(vector|list|map|set|deque|queue|stack|algorithm|iterator|unordered_map|unordered_set|multimap|multiset)>	STL コンテナ/アルゴリズムの include（08/09 以外は -42）'
	'std::[[:space:]]*(vector|list|map|set|deque|queue|stack|unordered_map|unordered_set|multimap|multiset)\b	STL コンテナの利用（08/09 以外は -42）'
)

# ファイルが属するモジュール番号（cppNN の NN）を返す。取れなければ空。
module_number() {
	local path="$1"
	if [[ "$path" =~ cpp([0-9]{2})/ ]]; then
		echo "${BASH_REMATCH[1]}"
	fi
}

# STL が許可されるモジュールか（08 / 09 のみ可）。
stl_allowed() {
	local num="$1"
	[ "$num" = "08" ] || [ "$num" = "09" ]
}

status=0
report() {
	# $1: ファイル, $2: 説明, $3: 該当行（grep -n 出力）
	echo "✖ 禁止事項を検出: $1 — $2" >&2
	printf '%s\n' "$3" | sed 's/^/    /' >&2
	status=1
}

for f in "${sources[@]}"; do
	num="$(module_number "$f")"

	# 常時禁止のパターン。
	for entry in "${always_forbidden[@]}"; do
		pattern="${entry%%	*}"
		desc="${entry#*	}"
		if hits="$(grep -nE "$pattern" "$f")"; then
			report "$f" "$desc" "$hits"
		fi
	done

	# STL は 08/09 以外で禁止。モジュール番号が取れない場合は安全側（禁止扱い）にする。
	if [ -z "$num" ] || ! stl_allowed "$num"; then
		for entry in "${stl_forbidden[@]}"; do
			pattern="${entry%%	*}"
			desc="${entry#*	}"
			if hits="$(grep -nE "$pattern" "$f")"; then
				report "$f" "$desc" "$hits"
			fi
		done
	fi
done

if [ "$status" -ne 0 ]; then
	echo >&2
	echo "✖ 禁止事項が含まれています。修正してから再コミットしてください。" >&2
fi

exit "$status"
