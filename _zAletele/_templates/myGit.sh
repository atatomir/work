echo '\nWelcome!\n\nCurrent Time : ';
date
echo '----------------------'
echo 'cd Desktop/work and pulling infos'

cd Desktop/work
git pull
git add .

echo '----------------------'
git status

echo '----------------------'
echo 'Commit name : update ???'
read name

echo '----------------------'
git commit -m "update "$name
git push

echo '\nDone'
echo '----------------------'
