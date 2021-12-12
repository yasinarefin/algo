# -*- coding: utf-8 -*-
"""
Created on Sun Dec 12 19:43:23 2021

@author: yasin
"""

def dec_to_bin_ibits(x, i):
    ret = bin(x)[2:]
    while len(ret) < i:
        ret = '0' + ret
    return ret

def binToDecIp(binIp):
    ip = ""
    for i in range(4):
        ip += str(int(binIp[8*i:8*i+8], 2)) +"." 
    return ip[:-1]
class IPV4:
    def __init__(self, ip):
        ipsub = ip.split('/')
        self.ipStr = ip
        self.ip = ipsub[0]
        self.sMask = ipsub[1]
        
    def ipString(self):
        return self.ipStr
    
    def maxHost(self):
        return 2**(32-int(self.sMask)) - 2
    
    def binForm(self):
        ipDiv = self.ip.split('.')
        ipStr = ""
        for i in ipDiv:
            ipStr += dec_to_bin_ibits(int(i), 8) + "."
        return ipStr[:-1]
    
    def subMaskBin(self):
        smask = "1" * int(self.sMask)
        while len(smask) != 32:
            smask += "0"
        return  smask
    
    def subMaskDec(self):
        return binToDecIp(self.subMaskBin())
    
    def ithHost(self, i):
        ip = self.binForm()
        ip = ip.replace(".", "")
        hostP = "0" * (32-int(self.sMask))
        add = int(hostP, 2) + i
        hp = dec_to_bin_ibits(add, len(hostP))
        
        return binToDecIp(ip[0:int(self.sMask)] + hp)
    
    def printBroadCast(self):
        print(self.ithHost(2**(32 - int(self.sMask))-1))
    
    def printClass(self):
        binf = self.binForm()
        if binf[0:4] == '1111':
            print("Experimental")
        elif binf[0:4] == '1110':
            print("Multicast")
        elif binf[0:3] == '110':
            print("Class C")
        elif binf[0:2] == '10':
            print("Class B")
        else: 
            print("CLass A")
        
    
    def subDiv(self, subIdLen):
        ip = self.binForm()
        ip = ip.replace(".", "")
        subId = "0" * subIdLen
        
        newIps = []
        
        for i in range(2**subIdLen):
            add = int(subId, 2) + i
            curSub = dec_to_bin_ibits(add, subIdLen)
            curIp = ip[0:int(self.sMask)] + curSub + "0" * (32-int(self.sMask) - subIdLen)
            curMask = int(self.sMask) + subIdLen
            newIps.append(IPV4(binToDecIp(curIp) + "/" + str(curMask)))
            
          #  print(binToDecIp(curIp) + "/" + str(curMask))
        return newIps
    
    def printSubDiv(self, subIdLen):
        subs = self.subDiv(subIdLen)
        for i in subs:
            print(i.ipString(), i.maxHost())
        
    
class IPV4Subnet():
    def __init__(self, ip, hostReq): #ipv4 and list of hostreq
        self.ip = ip
        self.hostreq = hostReq
        self.curHost = 0
    
    def rec(self, ip):
        if self.curHost >= len(self.hostreq):
            return 
        if self.hostreq[self.curHost] + 2 <= (ip.maxHost() + 2)/2:
            rp = ip.subDiv(1)
            self.rec(rp[0])
            self.rec(rp[1])
        else:
            print(self.curHost, ip.ipString())
            self.curHost += 1
            
        
    def subnetExec(self):
        self.curHost = 0
        self.rec(self.ip)
        
        

a= IPV4('172.200.160.0/20')
a.printSubDiv(3)
#b.subnetExec()

# a = IPV4('45.3.0.0/17')
# pr = a.subDiv(8)
# for i in pr:
#     print(i.maxHost())









