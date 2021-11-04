#!/bin/bash
set -e

NEWVERSION=$1

if [ -z $NEWVERSION ];then
	echo "podupdate.sh newVersion; example podupdate.sh 0.1.0"
	exit 1
fi

WORKDIR=`pwd`

echo " POD ======= UPDATE "
# 新增Pod的Git库标签，与修改podspec文件的版本号
./podup.sh $NEWVERSION MMLiveMediaSDK.podspec

# 提交新的库文件
echo " POD-GIT ======= COMMIT "
git add -A
git commit -m "pod update $NEWVERSION"
git push

echo " POD-GIT ======= NEW-TAG "
# 打新标签
git tag "$NEWVERSION"
git push --tags
echo " POD ======= PUSH "
# 发布podspec到远端的repo中
./podpush.sh -spec MMLiveMediaSDK.podspec -repo cosmos33 -force

echo " POD ======= DONE "
