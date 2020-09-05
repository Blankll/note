# git flow

1.  folk 项目到自己的目录下

2. git clone项目到自己的本地目录中

3. 进入到目录中添加上的游地址

   ```shell
   git remote add upstream upstreamaddress
   ```

   - upstream address 是上游的地址。

   - origin 自己的目录的地址

4. 拉取最新代码

   ```bash
   git pull upstream master
   git pull --rebase —autostash
   ```

5. 创建一个新的分支

6. 修改、添加

7. git commit

8. 切换到master分支

9. 拉取最先代码　git pull upstream master

10. check 到自己编写的代码分支

11. 执行 git rebase master 将自己的代码放到最上端

12. 先提交到自己folk的代码仓库中git push origin 分支名称

13. 在github中点击compare && pull request



## git 版本回退等操作

- 取消对文件的修改，还原到最近的版本
  ``git checkout -- <file>``
- 取消已经暂存的文件。即，撤销先前"git add"的操作
  ``git reset HEAD <file>...``
- 修改最后一次提交。用于修改上一次的提交信息，或漏提交文件等情况。
  ``git commit --amend``
- 回退所有内容到上一个版本
  ``git reset HEAD^``
- 回退a.py这个文件的版本到上一个版本  
  ``git reset HEAD^ a.py``
- 向前回退到第3个版本  
  ``git reset –soft HEAD~3``
- 将本地的状态回退到和远程的一样  
  ``git reset –hard origin/master``
- 回退到某个版本  
  ``git reset 057d``
- 回退到上一次提交的状态，按照某一次的commit完全反向的进行一次commit.(代码回滚到上个版本，并提交git)
  ``git revert HEAD``

