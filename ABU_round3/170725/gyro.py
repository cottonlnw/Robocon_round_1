import serial
import time

class UARTReceiver:
    def __init__(self, port='/dev/ttyAMA3', baudrate=115200, timeout=0.01, timeout_ms=100):
        self.ser = serial.Serial(port, baudrate, timeout=timeout)
        self.buffer = ""
        self.last_data_time = time.time()
        self.timeout_sec = timeout_ms / 1000.0  # แปลงเป็นวินาที
        self.last_valid_data = "0,0,0"
        print(f"UART รับข้อมูลที่ {port} เปิดใช้งานแล้ว")

    def receive(self):
        try:
            if self.ser.in_waiting > 0:
                raw = self.ser.read(self.ser.in_waiting).decode('utf-8', errors='ignore')
                self.buffer += raw

            while '<' in self.buffer and '>' in self.buffer:
                start = self.buffer.find('<')
                end = self.buffer.find('>', start)

                if end != -1:
                    data_str = self.buffer[start + 1:end].strip()
                    self.buffer = self.buffer[end + 1:]
                    self.last_data_time = time.time()
                    self.last_valid_data = data_str
                    return data_str

        except Exception as e:
            print(f"UART Error: {e}")

        # ถ้าไม่มีข้อมูลเข้ามาในช่วง timeout ให้ส่ง fallback
        if time.time() - self.last_data_time > self.timeout_sec:
            return "0,0,0"
        else:
            return self.last_valid_data  # ยังอยู่ในช่วง timeout → ใช้ค่าล่าสุด