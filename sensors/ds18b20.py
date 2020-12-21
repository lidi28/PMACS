import os

def getSensors():
    ds18b20 = []
    for i in os.listdir('/sys/bus/w1/devices'):
        if i.startswith('28'):
            ds18b20.append(i)
    return ds18b20

def read(ds18b20):
    location = '/sys/bus/w1/devices/' + ds18b20 + '/w1_slave'
    tfile = open(location)
    text = tfile.read()
    tfile.close()
    secondline = text.split("\n")[1]
    temperaturedata = secondline.split(" ")[9]
    temperature = float(temperaturedata[2:])
    celsius = temperature / 1000
    farenheit = (celsius * 1.8) + 32
    return ds18b20, celsius, farenheit

def kill():
    quit()

if __name__ == '__main__':
    try:
        serialNums = getSensors()
        for i in serialNums:
            if read(i) != None:
                print "Current temperature on %s : %0.3f C / %0.3f F" % (read(i)[0], read(i)[1], read(i)[2])
    except KeyboardInterrupt:
        kill()
