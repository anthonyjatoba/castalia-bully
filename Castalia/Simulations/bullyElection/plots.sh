# Variando o número de nós
rm *.txt && Castalia -c varyNumNodes

CastaliaResults -i *-*.txt -s "Consumed Energy" | CastaliaPlot -o plots/varyNumNodes/energyWithNumNodesVary.png -s histogram --invert -l left --xtitle="Num Nodes"
CastaliaResults -i *-*.txt -s "Remaining Energy" | CastaliaPlot -o plots/varyNumNodes/energyRemainWithNumNodesVary.png -s histogram --invert -l left --xtitle="Num Nodes" --yrange=18710:18720
CastaliaResults -i *-*.txt -s packets | CastaliaPlot -o plots/varyNumNodes/packetsSentWithNumNodesVary.png -s stacked --colors=radioBrdown -l "outside width -7" --xtitle="Num Nodes"

# Variando o Sigma e o TXpower
rm *.txt && Castalia -c varySigma,varyTxPower

CastaliaResults -i *-*.txt -s RX --filter-columns "Received with no interference" | CastaliaPlot -o plots/varySigma-varyTXpower/rxWithSigmaAndTxVary.png -s stacked
CastaliaResults -i *-*.txt -s RX --filter-columns Failed | CastaliaPlot -o plots/varySigma-varyTXpower/rxFailedWithSigmaAndTxVary.png -s stacked
CastaliaResults -i *-*.txt -s "Consumed Energy" | CastaliaPlot -o plots/varySigma-varyTXpower/consumedEnergyWithSigmaTXVary.png -s histogram
CastaliaResults -i *-*.txt -s packets | CastaliaPlot -o plots/varySigma-varyTXpower/packetsWithSigmaTXVary.png -s stacked
CastaliaResults -i *-*.txt -s TX | CastaliaPlot -o plots/varySigma-varyTXpower/packetsTXedWithSigmaTXVary.png

# Variando probabilidade de falha e recuperação
  rm *.txt && Castalia -c varyFailureP,varyRecoveryP

CastaliaResults -i *-*.txt -s RX --filter-columns "Received with no interference" | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/rxReceivedFailureRecoveryVary.png -s histogram
CastaliaResults -i *-*.txt -s RX --filter-columns Failed | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/rxFailedFailureRecoveryVary.png -s stacked
CastaliaResults -i *-*.txt -s "Consumed Energy" | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/consumedEnergyFailureRecoveryVary.png -s stacked
CastaliaResults -i *-*.txt -s "Remaining Energy" | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/remainingEnergyFailureRecoveryVary.png -s stacked
CastaliaResults -i *-*.txt -s TX | CastaliaPlot -o plots/varyFailureP-varyRecoveryP/txEdFailureRecoveryVary.png -s histogram
