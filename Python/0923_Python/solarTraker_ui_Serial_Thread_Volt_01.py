import sys
import serial
import time

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtWidgets import QApplication, QLabel, QVBoxLayout, QWidget



class Ui_MainWindow(QWidget):

    def __init__(self):
        super().__init__()
        self.label = QLabel("아두이노 데이터 대기중...")
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

        # 시리얼 쓰레드 실행
        self.thread = SerialThread(port="COM4", baudrate=9600)
        self.thread.data_received.connect(self.update_label)
        self.thread.start()


    def update_label(self, data):
        # 아두이노 데이터 출력
        #self.label.setText(str(data))
        _translate = QtCore.QCoreApplication.translate

        # 볼트표기
        self.label_4.setText(_translate("MainWindow", str(data['Volt'])))

        # 위치표기
        self.label_11.setText(_translate("MainWindow", str(data['A0'])))
        self.label_10.setText(_translate("MainWindow", str(data['A1'])))
        self.label_12.setText(_translate("MainWindow", str(data['A2'])))
        self.label_13.setText(_translate("MainWindow", str(data['A3'])))


    def closeEvent(self, event):
        # 창 닫을 때 쓰레드 종료
        self.thread.stop()
        event.accept()



    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(744, 677)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(170, 50, 121, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(170, 90, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(170, 120, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(300, 90, 111, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.label_6 = QtWidgets.QLabel(self.centralwidget)
        self.label_6.setGeometry(QtCore.QRect(300, 120, 31, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_6.setFont(font)
        self.label_6.setObjectName("label_6")
        self.label_7 = QtWidgets.QLabel(self.centralwidget)
        self.label_7.setGeometry(QtCore.QRect(300, 150, 31, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_7.setFont(font)
        self.label_7.setObjectName("label_7")
        self.label_8 = QtWidgets.QLabel(self.centralwidget)
        self.label_8.setGeometry(QtCore.QRect(300, 180, 31, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_8.setFont(font)
        self.label_8.setObjectName("label_8")
        self.label_9 = QtWidgets.QLabel(self.centralwidget)
        self.label_9.setGeometry(QtCore.QRect(300, 210, 31, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_9.setFont(font)
        self.label_9.setObjectName("label_9")
        self.label_10 = QtWidgets.QLabel(self.centralwidget)
        self.label_10.setGeometry(QtCore.QRect(360, 150, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_10.setFont(font)
        self.label_10.setObjectName("label_10")
        self.label_11 = QtWidgets.QLabel(self.centralwidget)
        self.label_11.setGeometry(QtCore.QRect(360, 120, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.label_12 = QtWidgets.QLabel(self.centralwidget)
        self.label_12.setGeometry(QtCore.QRect(360, 180, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_12.setFont(font)
        self.label_12.setObjectName("label_12")
        self.label_13 = QtWidgets.QLabel(self.centralwidget)
        self.label_13.setGeometry(QtCore.QRect(360, 210, 81, 31))
        font = QtGui.QFont()
        font.setFamily("맑은 고딕")
        font.setPointSize(14)
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(310, 250, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Noto Sans KR Black")
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton.setFont(font)
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(160, 250, 121, 41))
        font = QtGui.QFont()
        font.setFamily("Noto Sans KR Black")
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_2.setFont(font)
        self.pushButton_2.setObjectName("pushButton_2")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 744, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)


    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label_2.setText(_translate("MainWindow", "태양광 추적기"))
        self.label_3.setText(_translate("MainWindow", "생성 전압"))
        self.label_4.setText(_translate("MainWindow", "5V"))
        self.label_5.setText(_translate("MainWindow", "조도센서 값"))
        self.label_6.setText(_translate("MainWindow", "A0"))
        self.label_7.setText(_translate("MainWindow", "A1"))
        self.label_8.setText(_translate("MainWindow", "A2"))
        self.label_9.setText(_translate("MainWindow", "A3"))
        self.label_10.setText(_translate("MainWindow", "A1 value"))
        self.label_11.setText(_translate("MainWindow", "A0 value"))
        self.label_12.setText(_translate("MainWindow", "A2 value"))
        self.label_13.setText(_translate("MainWindow", "A3 value"))
        self.pushButton.setText(_translate("MainWindow", "정지"))
        self.pushButton_2.setText(_translate("MainWindow", "시작"))



def parse_line(line: str):

    """
    아두이노 시리얼 문자열을 파싱해서 딕셔너리로 변환
    예시 입력:
    "A0%73%A1%72%A2%78%A3%83%      X:110 Y:180      Left Down"
    """
    result = {}

    # 1) % 단위로 자르기
    parts = [p for p in line.split('%') if p.strip() != ""]

    # 2) A0, A1 ... 센서값 추출 (짝수=이름, 홀수=값)
    for i in range(0, len(parts) - 1, 2):
       
        if parts[i].startswith("A"):
            key = parts[i]
           
            try:
                value = int(parts[i + 1])
                result[key] = value

            except ValueError:
                continue

    # 3) 마지막 문자열에서 X, Y, 위치 정보 추출
    last_part = parts[-1].strip()
    tokens = last_part.split()

    for token in tokens:

        if token.startswith("X:"):
            result["X"] = int(token.replace("X:", ""))

        elif token.startswith("Y:"):
            result["Y"] = int(token.replace("Y:", ""))

    # X:, Y:가 아닌 부분은 pos로 저장
    others = [t for t in tokens if not t.startswith(("X:", "Y:"))]

    if others:
        result["pos"] = " ".join(others)


    # 4) Volt 처리
    if "Volt" in parts:
        volt_index = parts.index("Volt")
        if volt_index + 1 < len(parts):
            result["Volt"] = parts[volt_index + 1]
    

    return result


# --------------------------
# 시리얼 통신 쓰레드
# --------------------------
class SerialThread(QThread):
    data_received = pyqtSignal(dict)  # 딕셔너리 형태 데이터 전달

    def __init__(self, port="COM4", baudrate=9600):

        super().__init__()

        self.port = port
        self.baudrate = baudrate
        self.running = True

    def run(self):

        try:
            arduino = serial.Serial(self.port, self.baudrate, timeout=1)
            time.sleep(2)  # 아두이노 리셋 대기

            while self.running:

                if arduino.in_waiting > 0:
                    line = arduino.readline().decode('utf-8', errors='ignore').strip()

                    if line:
                        data = parse_line(line)
                        self.data_received.emit(data)

        except serial.SerialException as e:
            print("시리얼 연결 실패:", e)

    def stop(self):
        self.running = False
        self.wait()




# --------------------------
# 시리얼 통신 쓰레드
# --------------------------

class SerialThread(QThread):

    data_received = pyqtSignal(dict)  # 딕셔너리 형태 데이터 전달

    def __init__(self, port="COM4", baudrate=9600):
        super().__init__()
        self.port = port
        self.baudrate = baudrate
        self.running = True

    def run(self):
        try:
            arduino = serial.Serial(self.port, self.baudrate, timeout=1)
            time.sleep(2)  # 아두이노 리셋 대기
            
            while self.running:
                
                if arduino.in_waiting > 0:
                    line = arduino.readline().decode('utf-8', errors='ignore').strip()
                    
                    if line:
                        data = parse_line(line)
                        self.data_received.emit(data)
       
        except serial.SerialException as e:
            print("시리얼 연결 실패:", e)

    def stop(self):
        self.running = False
        self.wait()
        
if __name__ == "__main__":

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()

    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)

    MainWindow.show()

    sys.exit(app.exec_())
