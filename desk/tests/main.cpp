/****************************************************************************



*****************************************************************************/

#include "serialtoetherguiext.h"
#include <qapplication.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
  QApplication a (argc, argv);

  CAcquireDisplay *sertoetherObj = new CAcquireDisplay ();
  a.setMainWidget (sertoetherObj);
  sertoetherObj->setCaption ("Serial To Ethernet Converter");
  sertoetherObj->show ();
  return a.exec ();
}
