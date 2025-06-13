APK="$1"

if [ ! -f "$APK" ]; then
	echo "Please run $0 <PATH_TO_WINLATOR_10.0>.apk"
	exit 1
fi

if [ ! -f ~/Android/Sdk/ndk/27.0.12077973/build/cmake/android.toolchain.cmake ]; then
	echo "Make sure you have an Android SDK installed at ~/Android/Sdk (e.g. via Android Studio)"
	exit 1;
fi

mkdir -p build/lib/arm64-v8a

echo "Copying winlator into build/"
cp $APK build/base.apk

echo "Building libvortekpatcher.so"
cd libvortekpatcher
sh build.sh
cd -
cp libvortekpatcher/build/libvortekpatcher.so build/lib/arm64-v8a/

echo "Building libvortekrenderer.so"
uv run python patch_vortek.py prebuilts/libvortekrenderer.so
cp prebuilts/libvortekrenderer.so.new build/lib/arm64-v8a/libvortekrenderer.so
chmod +x build/libvortekrenderer.so

echo "Copying dump-api layer into build/"
cp prebuilts/libVkLayer_api_dump.so build/lib/arm64-v8a/
chmod +x build/libVkLayer_api_dump.so

echo "Adding libraries"
cd build
zip -u base.apk lib/arm64-v8a/libvortekrenderer.so
zip -u base.apk lib/arm64-v8a/libvortekpatcher.so
zip -u base.apk lib/arm64-v8a/libVkLayer_api_dump.so
cd -

java -Xmx256m -jar uber-apk-signer-1.3.0.jar -a build/base.apk --allowResign --overwrite
rm build/base.apk.idsig
rm -rf build/lib

echo "Patched Winlator built at base.apk"
adb install build/base.apk