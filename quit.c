void quit() {
	if (mounted == 1)
		close(file);
	printf("Exiting Minix shell.");
	exit(0);
}
