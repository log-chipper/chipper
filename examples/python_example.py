from ..clients.python.chipper_client import *

if __name__ == "__main__":
    c: ChipperClient = ChipperClient(service="python_example", source="example")
    c.log("info", "hello from python example")
    c.log("error", "something failed")
    c.close()

