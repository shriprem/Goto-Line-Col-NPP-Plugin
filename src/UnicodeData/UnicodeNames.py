import configparser

config = configparser.ConfigParser()

blocks = {line.split(';')[0] : line.split(';')[1].strip() 
          for line in open('blocks.txt', 'r') if not (line.startswith('#') or line.rstrip() == '')}

blockrange = {key.split('..')[0] : key.split('..')[1] for key in blocks.keys()}

def findBlock(cp):
    for lval, uval in blockrange.items():
        if (int(cp, 16) >= int(lval, 16) and int(cp, 16) <= int(uval, 16)):
            return blocks[lval + '..' + uval]

for key, value in blocks.items():
    config[value] = {}

for line in open('UnicodeData.txt', 'r'):
    cp = line.split(';')[0]
    alt = line.split(';')[10]
    config[findBlock(cp)][cp] = line.split(';')[1] if (alt == '') else alt
    
with open('UnicodeData.ini', 'w') as configFile:
    config.write(configFile, False)
