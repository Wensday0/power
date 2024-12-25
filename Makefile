compile: daemon_compile cli_compile

daemon_compile:
	gcc src/server.c src/fork_exec/fork_exec.c src/uds/uds.c -o power-daemon

cli_compile:
	gcc src/client.c src/uds/uds.c -o power


install: daemon_install cli_install

daemon_install:
	cp power-daemon /bin

cli_install:
	cp power /bin


uninstall: daemon_uninstall cli_uninstall

daemon_uninstall:
	rm /bin/power-daemon

cli_uninstall:
	rm /bin/power
