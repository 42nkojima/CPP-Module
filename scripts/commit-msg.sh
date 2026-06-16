#!/usr/bin/env bash
#
# commit-msg フック: Conventional Commits 準拠かを検証する。
# 使い方: scripts/commit-msg.sh <コミットメッセージファイルのパス>
#
# 形式: <type>(<scope>)?(!)?: <subject>
#   - type は許可リストのいずれか
#   - scope は任意
#   - 破壊的変更を示す "!" は任意
#   - subject は空でないこと
#
# マージコミット・fixup!/squash! コミットは検証をスキップする。

set -euo pipefail

msg_file="${1:?usage: commit-msg.sh <commit-msg-file>}"

# コメント行・空行を除いた最初の行（= subject 行）を取り出す。
subject="$(grep -v '^#' "$msg_file" | sed '/^[[:space:]]*$/d' | head -n 1 || true)"

# 検証をスキップするケース。
case "$subject" in
	"Merge "* | "Revert "* | "fixup! "* | "squash! "*)
		exit 0
		;;
esac

# 許可する type 一覧（Conventional Commits の慣例）。
types='feat|fix|docs|style|refactor|perf|test|build|ci|chore|revert'

# 形式チェック: type(scope)?!?: subject
pattern="^(${types})(\([a-z0-9._/-]+\))?(!)?: .+"

if printf '%s' "$subject" | grep -Eq "$pattern"; then
	exit 0
fi

cat >&2 <<EOF
✖ コミットメッセージが Conventional Commits 形式に従っていません。

  受け取った subject:
    ${subject:-(空)}

  期待する形式:
    <type>(<scope>)?(!)?: <subject>

  例:
    feat(cpp00): add Megaphone exercise
    fix: handle empty input
    docs(readme): explain build steps
    refactor(cpp02)!: change Fixed API

  許可する type:
    ${types//|/, }
EOF
exit 1
