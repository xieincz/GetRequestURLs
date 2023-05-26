rm -rf GetRequestURLs/usr
mkdir GetRequestURLs
mkdir GetRequestURLs/usr
mkdir GetRequestURLs/usr/bin
mkdir GetRequestURLs/usr/share
mkdir GetRequestURLs/usr/share/applications
mkdir GetRequestURLs/usr/share/icons


echo "place your GetRequestURLs.desktop file in GetRequestURLs folder"
echo "place your GetRequestURLs.png file in GetRequestURLs folder"


rm -rf GetRequestURLs/AppRun
rm -rf GetRequestURLs/usr/bin/qt.conf
rm -rf GetRequestURLs/usr/lib
rm -rf GetRequestURLs/usr/plugins
rm -rf GetRequestURLs/usr/translations
rm -rf GetRequestURLs/usr/doc

mkdir GetRequestURLs/usr/lib
cp -r /usr/lib/x86_64-linux-gnu/nss ./GetRequestURLs/usr/lib/
cp /home/tom/Qt/6.5.0/gcc_64/translations/qtwebengine* ./GetRequestURLs/usr/bin/
cp /home/tom/Qt/6.5.0/gcc_64/resources/* ./GetRequestURLs/usr/bin/
cp /home/tom/Qt/6.5.0/gcc_64/libexec/QtWebEngineProcess ./GetRequestURLs/usr/bin/



#cp -f ~/code/build-GetRequestURLs-Desktop_Qt_6_5_0_GCC_64bit-Release/GetRequestURLs ./GetRequestURLs/usr/bin/GetRequestURLs

cp -f ~/code/build-GetRequestURLs-Desktop_Qt_6_5_0_GCC_64bit-MinSizeRel/GetRequestURLs ./GetRequestURLs/usr/bin/GetRequestURLs


linuxdeployqt GetRequestURLs/usr/bin/GetRequestURLs -appimage -extra-plugins=iconengines,platformthemes/libqgtk3.so -no-copy-copyright-files
