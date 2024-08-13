

/*
        PROTOCOL MESSAGE REQUIREMENTS:

                PEER DISCOVERY
                --------------
                1. Version: Initiate handshake + add to node list
                2. VerAck: Accept handshake + add to node list
                3. ReqPeers: Request peer list from peer/boostrap
                4. SendPeers: Gives current peer list
                5. Ping: Heartbeat request
                6. Pong: Heartbeat response
                7. Exit: Tell peers that node is leaving network; delete from known nodes


                TRANSACTION PROPAGATION:
                ------------------------
                1. PropTx: Sends newly discovered tx hash to peers
                2. ReqTx: Peers w/o tx_hash knowledge ask for tx details
                3. SendTx: Nodes receiving ReqTx send tx details
                4. ReqMem: Request mempool txs for nodes starting up
                5. SendMem: Sends current mempool of txs


                BLOCK/BLOCKCHAIN PROPAGATION:
                ------------------
                1. PropBlk: Sends newly mined block hash + height to peers
                2. ReqBlk: Request blk details supply hash
                3. SendBlk: Sends blk details from ReqBlk request
                4. SendBlkHead: Sends blk header for blk hash
                5. ReqBlkChn: Request hashes of all blocks since height in chain


        PROTOCOL EXAMPLE SEQUENCES

                NODE STARTUP:
                -------------
                1. Connect to bootstrap nodes and receives peers list
                2. Initiate handshake with peers
                3. Requests node list from peers; peers send
                4. Get all nodes from peers, repeat until >= 10 nodes known
                5. Get entire blockchain (by block hashes) from every node; (handle forks)

                TRANSACTION PROPAGATION:
                ------------------------
                1. Node A receives new tx from wallet
                2. Sends tx hash to peers
                3. Peers who don't know hash send req to get tx details
                4. Node A sends details; tx propagates
                5. Peers validate tx and add to mempool

                BLOCK PROPAGATION:
                ------------------
                1. Node A mines new block with POW
                2. Sends block hash + height to peers
                3. Peers who don't know block + no forks get more info
                4. Node A sends info; block propagates P2P
                5. Block is officially added to chain; tx and miner rewards added

*/
