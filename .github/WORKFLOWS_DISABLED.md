# GitHub Actions disabled on ev9-sunnypilot

This branch preserves the Sunnypilot source from commit
`5928a37ad18783068ee26b187f6a7ddb9ff9c3d3`, immediately before the StarPilot
migration in `450f7cafe79611f91894e14373c488b38b48c915`.

The original `.github/workflows/` directory is preserved unchanged as
`.github/workflows-disabled/`. No active workflow files remain on this branch.
The application source is unchanged from the original commit.

Keep the archived workflows outside `.github/workflows/` so this branch has no
GitHub Actions build or deployment workflows. Do not restore them or manually
run the archived publication scripts without reviewing their destination branches.

Repository automation on other branches is unchanged. In particular, the
`master` deployment-sync workflow listens for prebuilt runs from `ev9-dev`.
Opening pull requests or triggering repository-wide events can still invoke
workflows from their base/default branch.
