
if [[ ! -p /tmp/mylog.fifo ]]; then
    echo "Pipe /tmp/mylog.fifo does not exist."
    exit 1
fi

while true; do
    echo "OK" > /tmp/mylog.fifo
    sleep 3
done
