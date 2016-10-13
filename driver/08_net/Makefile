CC = arm-linux-gcc


libztnet.so :
	$(CC) -shared -fPIC -Wall -o libztnet.so net_interface.cpp csocket.cpp -I./ -L./ 
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf libztnet.so
	rm -rf *.bak
