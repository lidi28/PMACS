from gpiozero import Button
water_sensor = Button(17)
water_sensor.wait_for_press()
print('Reached top')