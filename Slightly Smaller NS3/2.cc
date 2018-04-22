// Network topology
//
//       n0    n1   n2   n3
//       |     |    |    |
//       =================
//              LAN
//
// - UDP flows from n0 to n1 and back

#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int 
main (int argc, char *argv[])
{

	NodeContainer n;
	n.Create (4);
	InternetStackHelper stack;
	stack.Install (n);
	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", StringValue("5Mbps"));
	csma.SetChannelAttribute ("Delay",    StringValue("2ms"));
	csma.SetDeviceAttribute  ("Mtu",      StringValue("1400"));
	NetDeviceContainer d = csma.Install (n);

	Ipv4AddressHelper ipv4;
	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i = ipv4.Assign (d);

  UdpEchoServerHelper server (9);

  UdpEchoClientHelper client (i.GetAddress(1), 9);
  client.SetAttribute ("MaxPackets", StringValue("4"));
  client.SetAttribute ("Interval",   StringValue("1s"));
  client.SetAttribute ("PacketSize", StringValue("11024"));

  ApplicationContainer apps;
  apps = server.Install (n.Get (1));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  apps = client.Install (n.Get (0));
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));

	AnimationInterface anim ("second.xml");
	Simulator::Run ();
	Simulator::Destroy ();

}
