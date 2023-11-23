import cv2 as cv
import numpy as np
import argparse


def image2bin(path: str):
    image = cv.imread(path)

    save_path = str(path)
    save_path = save_path.split(".", -1)[0] + "_"
    save_path = save_path + str(image.shape[0]) + "_" + \
        str(image.shape[1]) + "_" + str(image.shape[2]) + ".bin"
    image_array = np.array(image)
    image_array = image_array.flatten()
    print('{}--->{}; total: {}'.format(path, save_path, image_array.size))
    image_array.tofile(save_path)


def bin2image(path: str, shape_str: str):
    shape_str = shape_str.split(',')
    shape = [int(shape_str[0]), int(shape_str[1]), int(shape_str[2])]
    data = np.fromfile(path, dtype=np.uint8)
    data = data.reshape(shape)
    save = path.split(".")[0]+".jpg"
    cv.imwrite(save, data)
    pass


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="图片转换工具")
    parser.add_argument("-p", "--path", required=True)
    parser.add_argument('-m', "--mode", type=int,
                        default=0, help='mode: 0是图片转成二进制文件,1是二进制文件转成图片,注意当输入模式1的时候必须明确图片的维度')
    parser.add_argument(
        "-s", "--shape", type=str, help='请用逗号隔开,如 224,224,3')
    args = parser.parse_args()
    if (args.mode == 0):
        image2bin(args.path)
    else:
        bin2image(args.path, args.shape)
