
typedef port_data
{
   ring_t* rx_ring;
   ring_t* tx_ring;
   int rx_ring_count;
   int tx_ring_count;
}

typedef core_data
{
	tiny_pool_t tx_mbuf[SF_MAX_PORTS];
	int port_tx_map[SF_MAX_PORTS];
	int port_rx_map[SF_MAX_PORTS];
	int port_bind[SF_MAX_PORTS];
	int port_bind_count;	
}
