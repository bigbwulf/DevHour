## git
* A version control system tracks and manages changes to software code
* There have been many version control systems over the years and many current alternatives
  * RCS, CVS, Subversion
  * Perforce, Bazaar, Mercurial
* Git is the undisputed king
* Created by Linus Torvalds to host the Linux Kernel, designed to be used by a Unix-like command line
* Git is complex and has a steep learning curve, but we can still be productive with a relatively small set of commands

![Haha xkcd](https://imgs.xkcd.com/comics/git.png)

### config 
Set up your commit data and utilities

```bash
$ git config --global user.name "ajb"
$ git config --global user.email "ajb@aol.com"

# Git opens a text editor everytime we commit
# Be careful! vi is the default! Gross!
$ git config --global core.editor emacs

git config --global init.defaultBranch main

git config --global color.ui "auto"
```
### create a new repository

```bash
$ mkdir project && cd project
$ git init
```

### workflow
There are three trees in git:
  * Working Directory - the actual files
  * Index - staging areas
  * HEAD - points to the last commit
![workflow](https://rogerdudler.github.io/git-guide/img/trees.png)

Once we add a file, we can use ```git status``` to see what's going on 

```bash
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
	modified:   Makefile

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	git.md

no changes added to commit (use "git add" and/or "git commit -a")

```

We can propose changes (add to index) using ```git add```

``` bash
$ git add -A
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	modified:   Makefile
	new file:   git.md
```

Finally to commit, we use ```git commit``` to commit to the HEAD (but not the remote repository)
[Commit](https://onlywei.github.io/explain-git-with-d3/#commit) creates a new snapshot of the index and moves the HEAD pointer

```bash
$ git commit -m "Demostrating Commit"
[main f45b988] Demostrating Commit
 4 files changed, 152 insertions(+)
```

if you misspell something like an idiot, use:

``` bash
$ git commit --amend -m "Demonstrating Commit"
```

To view the diff between between last commit and unstaged changes, use ```git diff```

``` bash
> git diff
diff --git a/git.md b/git.md
index 2e2e3df..5362b5a 100644
--- a/git.md
+++ b/git.md
@@ -85,4 +85,5 @@ $ git commit -m "Demostrating Commit"
 $ git commit --amend -m "Demonstrating Commit"
 
 +* To view the diff between between last commit and unstaged changes,  use git diff

 ```
 
 * if you want to see the difference between staged changes and previous version of the repo, use ```git diff --staged```
 
 ### branching

[Branches](https://onlywei.github.io/explain-git-with-d3/#branch) are used to develop features isolated from each other

![Branches](https://rogerdudler.github.io/git-guide/img/branches.png)

Create a new branch and switch it it:

``` bash
$ git checkout -b newBranch

# switch back to main
$ git checkout main

# delete the branch
git branch -d newBranch

# push the branch to a remote repo
$ git push origin <branch>
```

 
### remote repository

We create a working copy of remote repository by running

``` bash
> git clone /path/to/repository/
```

if you have not cloned a repo and want to connect your local repo to a remote, add it with:
``` bash
git remote add <name> <url>
```

to view your remote repos, use:

``` bash
$ git remote -v
```


### update and merge
To update your local repository to the newest commit:

```bash
$ git pull
```

This [*fetches*](https://onlywei.github.io/explain-git-with-d3/#fetch) (updates remote tracking branches) and [*merges*](https://onlywei.github.io/explain-git-with-d3/#merge) your current HEAD, while the command

```bash
$ git merge <branch>
```

will merge another branch into your active branch. Both are not always possible and may result in merge conflicts. These conflicts must be resolved by editing the source files. 

Mark files as merged with: 

```bash
git add <filename>
```

### push
[git push](https://onlywei.github.io/explain-git-with-d3/#push) will send  commits on your local branch that the origin does not have. All pushes must cause a fast-forward merge. 

``` bash
git push <name> <branch>
```

### replace local changes

To replace changes in your working tree (working directory) with the last content in HEAD: 

```bash
$ git checkout -- <filename>
```

If you want to drop all your local changes and commits, use [reset](https://onlywei.github.io/explain-git-with-d3/#reset): 

```bash
$ git fetch origin
$ git reset --hard origin/main
```

### references and further reading (in order of complexity)

https://rogerdudler.github.io/git-guide/

https://practical-neuroimaging.github.io/git_parable.html

https://matthew-brett.github.io/curious-git/

