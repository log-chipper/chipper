import socket

class ChipperClient:
    def __init__(self, socket_path: str ="/tmp/chipper.sock", service: str = "myapp", source: str = "worker") -> None:
        self.socket_path = socket_path
        self.service = service
        self.source = source
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)

    def log(self, level: str, msg: str) -> None:
        # level=info service=pyapp source=worker msg="something"
        line = f'level={level} service={self.service} source={self.source} msg="{msg}"'
        self.sock.sendto(line.encode("utf-8"), self.socket_path)

    def close(self) -> None:
        self.sock.close()
