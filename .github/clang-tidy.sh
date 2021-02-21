#!/usr/bin/env bash
clang-tidy --checks=-*,bugprone-*,-bugprone-infinite-loop,performance-*,readability-*,misc-* --warnings-as-errors=* "$@" --
