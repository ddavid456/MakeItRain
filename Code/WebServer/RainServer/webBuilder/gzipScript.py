import os
import gzip
import subprocess
import time


localPathIngest = './buildContent/ingest/'
localPathVomit = './buildContent/vomit/'


def buildTemplate(gzipContent: bytes, fileName: str):
    fileString = fileName.split('.')[0]
    hexData = ", ".join(["0x%0.2X" % byt for byt in gzipContent])
    headerString = f'// This content is autogenerated do not edit. File Content:{fileName} '
    buildStringLength = f'const uint16_t PAGE_{fileString}_L = {len(gzipContent)};'
    buildStringContent = f'const uint8_t PAGE_{fileString}[] PROGMEM = {{{hexData}}};'

    with open(localPathVomit+"html_"+fileString+".h", 'w+') as f:
        for content in [headerString, buildStringLength, buildStringContent]:
            f.write('\n')
            f.write(content)


# Convert to gzip
for file in os.listdir(localPathIngest):
    if file not in [".gitkeep", ".DS_Store"]:
        with open(localPathIngest + file, 'rb') as f:
            print("Converting ", file)
            buildTemplate(gzip.compress(f.read()), file)

time.sleep(1)
# Format all header files to look pretty
for file in os.listdir(localPathVomit):
    if file not in [".gitkeep", ".DS_Store"]:
        subprocess.run(["c_formatter_42", f'buildContent/vomit/{file}'])

exit()