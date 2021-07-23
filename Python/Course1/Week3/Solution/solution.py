class CarBase:
    def __init__(self, photo_file_name, brand, carrying):
        self.photo_file_name = photo_file_name
        self.brand = brand
        self.carrying = carrying

    def get_photo_file_ext(self):
        pass


class Car(CarBase):
    pass


class Truck(CarBase):
    def __init__(self):
        super().__init__(self)


class SpecMachine(CarBase):
    pass
