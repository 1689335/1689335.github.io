# encoding: utf-8

import os

def convert(src):

	for root, ds, files in os.walk(src):
		for f in files:
			name = os.path.basename(f)
			print(unicode(name, encoding="utf-8"))
			if not name.endswith(".cpp"):
				continue

			idx, desc, postfix = name.split('.')

			with open(os.path.join("code", desc + ".md"), "w") as wfd:
				wfd.write("---\n")
				wfd.write("sort: " + str(idx))
				wfd.write("\n---")
				wfd.write("\n\n```\n")

				with open(root + f, "r") as rfd:
					content = rfd.readlines()
					for line in content:
						wfd.write(line)

				wfd.write("\n```\n")
				

if __name__ == "__main__":
	if len(os.sys.argv) == 1:
		src = "../../leetcode/src/"
	else:
		src = os.sys.argv[1]

	convert(src)
