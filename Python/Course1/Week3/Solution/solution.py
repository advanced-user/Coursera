import os.path
import csv


class CarBase:
    def __init__(self, car_type, brand, photo_file_name, carrying):
        try:
            if photo_file_name == '' or brand == '':
                raise ValueError

            self.photo_file_name = photo_file_name
            self.checking_the_path_to_the_photo()

            self.car_type = car_type
            self.brand = brand
            self.carrying = float(carrying)
        except Exception:
            raise

    def checking_the_path_to_the_photo(self):
        split_path = os.path.splitext(self.photo_file_name)
        if split_path[1] != '.jpg' and split_path[1] != '.jpeg' and split_path[1] != '.png' and split_path[1] != '.gif':
            raise Exception

    def get_photo_file_ext(self):
        return os.path.splitext(self.photo_file_name)[1]


class Car(CarBase):
    def __init__(self, brand, photo_file_name, carrying, passenger_seats_count):
        try:
            self.passenger_seats_count = int(passenger_seats_count)
            super().__init__('car', brand, photo_file_name, carrying)
        except Exception:
            raise


class Truck(CarBase):
    def __init__(self, brand, photo_file_name, carrying, body_whl):
        try:
            self.body_whl = body_whl
            self._body_length = 0.0
            self._body_width = 0.0
            self._body_height = 0.0

            super().__init__('truck', brand, photo_file_name, carrying)
        except Exception:
            raise

    @property
    def body_length(self):
        self.set_values()

        return self._body_length

    @property
    def body_width(self):
        self.set_values()

        return self._body_width

    @property
    def body_height(self):
        self.set_values()

        return self._body_height

    def set_values(self):
        dimensions = self.body_whl.split('x')
        try:
            if len(dimensions) != 3:
                raise ValueError

            self._body_length = float(dimensions[0])
            self._body_width = float(dimensions[1])
            self._body_height = float(dimensions[2])
        except ValueError:
            self._body_length = 0.0
            self._body_width = 0.0
            self._body_height = 0.0

    def get_body_volume(self):
        return self.body_height * self.body_length * self.body_width


class SpecMachine(CarBase):
    def __init__(self, brand, photo_file_name, carrying, extra):
        try:
            if extra == '':
                raise ValueError

            self.extra = extra
            super().__init__('spec_machine', brand, photo_file_name, carrying)
        except Exception:
            raise


def get_car_list(csv_filename):
    car_list = []

    with open(csv_filename) as csv_fd:
        reader = csv.reader(csv_fd, delimiter=';')
        next(reader)  # пропускаем заголовок
        for row in reader:
            try:
                if row[0] == 'car':
                    car = Car(row[1], row[3], row[5], row[2])
                elif row[0] == 'truck':
                    car = Truck(row[1], row[3], row[5], row[4])
                elif row[0] == 'spec_machine':
                    car = SpecMachine(row[1], row[3], row[5], row[6])
                else:
                    raise Exception
                car_list.append(car)
            except Exception:
                continue

    return car_list
