#include "AndroidUtils.h"

std::string AndroidUtils::getRealFilePath(const std::string &path)
{
	QString filename = "";

#ifdef	ANDROID
	QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod(
			"android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",
			QAndroidJniObject::fromString(path.c_str()).object<jstring>());

	filename =
			QAndroidJniObject::callStaticObjectMethod(
					"pl/daviss/davissapp/QSharePathResolver", "getRealPathFromURI",
					"(Landroid/content/Context;Landroid/net/Uri;)Ljava/lang/String;",
					QtAndroid::androidContext().object(), uri.object())
					.toString();

	return filename.toStdString();
#endif

	return filename.toStdString();
}
