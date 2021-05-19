# Firewall config
bash /home/santiago/git/PINISAT/ConfigScripts/firewallconfig.sh $1 192.168.4.1
# Start database / ensure other servers are down
sudo systemctl stop mysql.service
sudo docker start pinisat_db
# Ensure grafana is up
sudo systemctl start grafana-server
# Run server
python3 /home/santiago/git/PINISAT/Sources/Server/server.py $1&
# Run grafana
firefox http://localhost:3000/d/nQsx1_CMz/pinisat-control?orgId=1&refresh=5s
