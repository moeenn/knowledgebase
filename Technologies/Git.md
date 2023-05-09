```bash
# List all local branches
$ git branch


# Create new Branch
$ git branch <branch-name>


# Create new Branch and Switch to it
$ git branch -b <branch-name>


# Push new branch to remote
$ git push -u origin <branch-name>


# Change current Branch
$ git checkout <branch-name>
# OR
$ git switch <branch-name>


# Rename current branch
$ git branch -m <new-name>


# Delete Local Branch
$ git branch -D <branch-name>


# Delete remote branch
$ git push origin --delete <branch-name>


# Pull code from another branch into current branch
$ git pull origin <other-branch-nam>
```