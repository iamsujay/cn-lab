#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;
int
main (int argc, char *argv[])
{

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute("Delay",   StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = p2p.Install(nodes);

  InternetStackHelper stack;
  stack.Install(nodes);

  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", StringValue ("1"));
  echoClient.SetAttribute ("Interval",   StringValue("1s"));
  echoClient.SetAttribute ("PacketSize", StringValue("1024"));

  ApplicationContainer apps;
  apps = echoServer.Install (nodes.Get (1));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  apps = echoClient.Install (nodes.Get (0));
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));

  AnimationInterface anim ("first.xml");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
