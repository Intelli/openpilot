# from the root of Intelli/sunnypilot
SUBPATH=opendbc_repo

# 1) Pull the latest commit of the tracked branch into the submodule worktree
git submodule update --remote "$SUBPATH"

# 2) Record the new submodule commit in the superproject
git add "$SUBPATH"
git commit -m "Bump opendbc submodule to latest Intelli/opendbc@hkg-angle-steering-2025"
git push

