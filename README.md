# cppApps
To download one folder(project) with GIT:<br>
mkdir test1 & cd test1 & git init & git remote add origin https://github.com/dimeddy46/cppApps.git & git config core.sparseCheckout true & echo <b>[changeThisWithFolderName]</b>/* > .git/info/sparse-checkout & git fetch origin & git checkout origin/master
<br><br>
And maybe other projects:<br>
echo <b>[AnotherFolderName]</b>/* >> .git/info/sparse-checkout & git checkout master
