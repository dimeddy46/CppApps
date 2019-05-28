# C++ Applications

<b>To download only one folder(project) with GIT:</b><br>
mkdir test1 & cd test1 & git init & git remote add origin https://github.com/dimeddy46/CppApps.git & git config core.sparseCheckout true & echo <b>[changeThisWithApplicationName]</b>/* > .git/info/sparse-checkout & git fetch & git checkout master
<br><br>
<b>More projects:</b><br>
echo <b>[anotherApplicationName]</b>/* >> .git/info/sparse-checkout & git checkout master<br><br>
<b>Clear:</b><br> git config core.sparseCheckout false & rd /s test1
