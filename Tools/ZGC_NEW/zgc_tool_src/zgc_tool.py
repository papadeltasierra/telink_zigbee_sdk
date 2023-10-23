import sys
from PyQt5 import QtWidgets
from hcisendcommand import Pyqt5Serial


if __name__ == '__main__':
    # Use parse_known_args() here to provide help and exit if help is requested.
    app = QtWidgets.QApplication(sys.argv)  #初始化app
    myshow = Pyqt5Serial(app)               #创建主窗口
    myshow.show()                           #显示窗口
    sys.exit(app.exec_())                   #消息循环结束之后返回0，接着调用sys.exit(0)退出程序
