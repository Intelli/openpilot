# from the root of Intelli/sunnypilot
SUBPATH=opendbc_repo

# 1) Initialize and sync the submodule configuration (in case .gitmodules changed)
git submodule sync "$SUBPATH"

# 2) Ensure the submodule is properly initialized
git submodule update --init "$SUBPATH"

# 3) Go into the submodule and ensure it's tracking the correct remote and branch
cd "$SUBPATH"
git remote set-url origin https://github.com/Intelli/opendbc.git
git fetch origin
git checkout -B hkg-angle-steering-2025 origin/hkg-angle-steering-2025
cd ..

# 4) Pull the latest commit of the tracked branch into the submodule worktree
git submodule update --remote "$SUBPATH"

# 5) Record the new submodule commit in the superproject
git add "$SUBPATH"
git commit -m "Bump opendbc submodule to latest Intelli/opendbc@hkg-angle-steering-2025"
git push

