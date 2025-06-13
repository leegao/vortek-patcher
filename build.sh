cp /home/leegao/AndroidStudioProjects/DummyVk/app/build/intermediates/cxx/Debug/1695t2m5/obj/arm64-v8a/libdummyvk.so /home/leegao/Downloads/Winlator_10.0.apk-decompiled/lib/arm64-v8a/libdummyvk.so

java -Xmx256m -jar /home/leegao/Downloads/apktool_2.11.1.jar b /home/leegao/Downloads/Winlator_10.0.apk-decompiled --use-aapt2
java -Xmx256m -jar /home/leegao/Downloads/uber-apk-signer-1.3.0.jar -a /home/leegao/Downloads/Winlator_10.0.apk-decompiled/dist/Winlator_10.0.apk --allowResign --overwrite

# /home/leegao/Downloads/Winlator_10.0.apk-decompiled/dist/Winlator_10.0.apk
rm /home/leegao/Downloads/Winlator_10.0.apk-decompiled/dist/Winlator_10.0.apk.idsig
adb install /home/leegao/Downloads/Winlator_10.0.apk-decompiled/dist/Winlator_10.0.apk