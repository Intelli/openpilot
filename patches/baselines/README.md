# Patch preimages

Files named by a Git blob ID contain that blob's exact original bytes. They are
maintenance data, excluded from source patch exports and from patch replay.
Committing them makes the preimage objects referenced by feature patches reachable
after fresh or shallow clones, including intermediate versions of shared files.

The feature updater can add new payloads when a preceding feature changes a later
feature's baseline. Review and stage them with the corresponding patch. Do not
edit payloads in place: their Git blob IDs must match their filenames.
