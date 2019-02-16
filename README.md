# cppApps
To download only one folder(project) with GIT:<br>
mkdir test1 & cd test1 & git init & git remote add origin https://github.com/dimeddy46/cppApps.git & git config core.sparseCheckout true & echo <b>[changeThisWithFolderName]</b>/* > .git/info/sparse-checkout & git fetch & git checkout master
<br><br>
..or more projects:<br>
echo <b>[AnotherFolderName]</b>/* >> .git/info/sparse-checkout & git checkout master
