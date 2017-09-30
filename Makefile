.PHONY:all
all:
	git fetch
	git add --all
	git commit -m "updates"
	git pull
