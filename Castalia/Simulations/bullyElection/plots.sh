# Variando o número de nós
rm *.txt && Castalia -c varyNumNodes -r 10

CastaliaResults -i *-*.txt -s "Consumed Energy" -c 95 | CastaliaPlot -o plots/varyNumNodes/energyConsumedWithNumNodesVary.png --title "Consumed energy x Number of nodes" --ltitle="Consumed Energy" --xtitle="Num Nodes"
CastaliaResults -i *-*.txt -s "Remaining Energy" -c 95 | CastaliaPlot -o plots/varyNumNodes/energyRemainWithNumNodesVary.png --title "Remaining energy x Number of nodes" --ltitle="Remaining Energy" --xtitle="Num Nodes"
CastaliaResults -i *-*.txt -s packets | CastaliaPlot -o plots/varyNumNodes/packetsSentWithNumNodesVary.png -s stacked -l out --title "Packets sent x Number of nodes" --ltitle="Packet Type"
CastaliaResults -i *-*.txt -s RX --filter-columns="Received with no interference" | CastaliaPlot -o plots/varyNumNodes/rxReceivedWithNumNodesVary.png -s histogram --invert --title "Transmissions succeed with no interference" --ltitle="Num Nodes"
CastaliaResults -i *-*.txt -s RX --filter-columns="Failed" | CastaliaPlot -o plots/varyNumNodes/rxFailedWithNumNodesVary.png -s stacked -l "top left" --title "Number of nodes x Transmissions failed" --ltitle="Fail Type"

# Variando o Sigma e o TXpower
rm *.txt && Castalia -c varySigma,varyTxPower -r 10

CastaliaResults -i *-*.txt -s "Consumed Energy" -c 95 | CastaliaPlot -o plots/varySigma-varyTXpower/consumedEnergyWithSigmaTXVary.png --title "Consumed energy x Number of nodes" --ltitle="Consumed Energy" --xtitle="Num Nodes"
CastaliaResults -i *-*.txt -s "Remaining Energy" -c 95 | CastaliaPlot -o plots/varySigma-varyTXpower/remainingEnergyWithSigmaTXVary.png --title "Remaining energy x Number of nodes" --ltitle="Remaining Energy" --xtitle="Num Nodes"
CastaliaResults -i *-*.txt -s packets | CastaliaPlot -o plots/varySigma-varyTXpower/packetsSentWithSigmaTXVary.png -s stacked -l out --title "Packets sent x Number of nodes" --ltitle="Packet Type"
CastaliaResults -i *-*.txt -s RX --filter-columns="Received with no interference" | CastaliaPlot -o plots/varySigma-varyTXpower/rxReceivedWithSigmaAndTxVary.png -s histogram --invert --title "Transmissions succeed with no interference" --ltitle="Num Nodes"
CastaliaResults -i *-*.txt -s RX --filter-columns="Failed" | CastaliaPlot -o plots/varySigma-varyTXpower/rxFailedWithSigmaAndTxVary.png -s stacked -l "top left" --title "Number of nodes x Transmissions failed" --ltitle="Fail Type"

# Variando probabilidade de falha e recuperação
rm *.txt && Castalia -c varyFailureP,varyRecoveryP -r 10

CastaliaResults -i *-*.txt -s "Consumed Energy" -c 95 | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/consumedEnergyFailureRecoveryVary.png --title "Consumed energy" --ltitle="Failure Probability" --xtitle="Recovery Probability"
CastaliaResults -i *-*.txt -s "Remaining Energy" -c 95 | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/remainingEnergyFailureRecoveryVary.png --title "Remaining energy" --ltitle="Failure Probability" --xtitle="Recovery Probability"
CastaliaResults -i *-*.txt -s packets | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/packetsSentFailureRecoveryVary.png -s stacked -l out --title "Packets sent" --ltitle="Packet Type" --xtitle="Failure Probability, Recovery Probability"
CastaliaResults -i *-*.txt -s RX --filter-columns="Received with no interference" | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/rxReceivedFailureRecoveryVary.png -s histogram --invert --title "Transmissions succeed with no interference" --ltitle="Recovery Probability" --xtitle="Failure Probability"
CastaliaResults -i *-*.txt -s RX --filter-columns="Failed" | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/rxFailedFailureRecoveryVary.png -s stacked -l "top left" --title "Transmissions failed" --ltitle="Fail Type" --xtitle="Failure Probability, Recovery Probability"

CastaliaResults -i diagonalSink -s RX
--filter-columns="Failed with no |Received with no" -p |
CastaliaPlot -o diagonalSinkPckgs.jpg
-s histogram -l out --title "Delivery succes x number of nodes - Diagonal sink"
--hist-gap=5 --ltitle="Number of nodes"
