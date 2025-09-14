git fetch upstream hkg-angle-steering-2025 --prune
git restore --source=upstream/hkg-angle-steering-2025 --staged --worktree --no-overlay -- \
  . \
  ':(top,exclude)AGENTS.md' \
  ':(top,exclude)sync-upstream.sh' \
  ':(top,exclude)update.sh' \
  ':(top,exclude).gitmodules' \
  ':(top,exclude)ev9_panda_safety.patch' \
  ':(top,exclude)opendbc_repo'
#git restore --source=upstream/hkg-angle-steering-2025 --staged --worktree --no-overlay .
#git clean -fd
#git commit -m "Sync upstream"
#git push origin hkg-angle-steering-2025
