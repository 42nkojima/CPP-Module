#!/usr/bin/env bash
#
# 差分のあった cppNN/exNN/ を 42 の採点フラグでビルドして弾く。
# 使い方: scripts/check-build.sh <path...>  (lefthook の {staged_files})

set -euo pipefail

CXX="c++"
CXXFLAGS="-Wall -Wextra -Werror -std=c++98"

# 全モジュールの再ビルドを避けるため、対象ファイルが属する exNN だけに絞る。
modules=()
for f in "$@"; do
	if [[ "$f" =~ ^(cpp[0-9]{2}/ex[0-9]{2})/ ]]; then
		modules+=("${BASH_REMATCH[1]}")
	fi
done

if [ "${#modules[@]}" -eq 0 ]; then
	exit 0
fi

mapfile -t modules < <(printf '%s\n' "${modules[@]}" | sort -u)

status=0
for dir in "${modules[@]}"; do
	if [ ! -d "$dir" ]; then
		continue
	fi

	echo "▶ build: $dir"
	if [ -f "$dir/Makefile" ]; then
		# Makefile があれば提出物と同じ経路で make に任せる。
		if ! make -C "$dir"; then
			echo "✖ build failed: $dir (make)" >&2
			status=1
		fi
	else
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
