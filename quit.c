void quit() {
	if (mounted == 1)
		close(file);
	exit(0);
}
