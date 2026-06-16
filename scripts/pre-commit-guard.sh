#!/usr/bin/env bash
#
# pre-commit 土台の発火確認用スクリプト。
# lefthook の pre-commit フックが正しくインストール・発火することを確認するための最小チェック。
# ビルド / format / grep / lint などの個別チェックを追加したら、この guard は削除してよい。

set -euo pipefail

echo "pre-commit hook fired (guard)."
exit 0
