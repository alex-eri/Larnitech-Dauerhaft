/*
<?xml version="1.0" encoding="UTF-8"?>
<xml>
    <description>
        <b>control DAUERHAFT via RS485</b>
    </description>

    <tag value="import-script" />

    <item type="number" name="ID" value="1" required="1" min="1" max="99" comment="Адрес мотора штор" width="170" />
    <item type="number" name="NumCh" value="1" required="1" min="0" max="16" comment="Количество каналов" Width="170" />
    <item type="devices-list" name="RS485" filter="com-port" required="1" comment="RS485" />
    <item type="hidden" name="BLINDS" value="%TARGET%" />

    <additems>
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="101" name="Штора 1" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="102" name="Штора 2" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="103" name="Штора 3" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="104" name="Штора 4" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="105" name="Штора 5" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="106" name="Штора 6" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="107" name="Штора 7" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="108" name="Штора 8" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="109" name="Штора 9" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="110" name="Штора 10" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="111" name="Штора 11" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="112" name="Штора 12" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="113" name="Штора 13" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="114" name="Штора 14" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="115" name="Штора 15" type="blinds" virtual="yes" />
        <additem tag="item" hw="dim=0" id="%TARGET%" sub-id="116" name="Штора 16" type="blinds" virtual="yes" />
    </additems>
</xml>
*/

u8 readchan = 1;

void sendCommand(u8 Channel, u8 cmd, u8 subcmd) {
  u8 chlow = (1 << (Channel - 1)) & 0xff;
  u8 chhigh = (1 << (Channel - 1)) >> 8 & 0xff;
  if (Channel == 0) {
    chlow = 0xff;
    chhigh = 0xff;
  }
  setStatus(RS485, {0x9a, ID, chlow, chhigh, cmd, subcmd,
                    ID ^ chlow ^ chhigh ^ cmd ^ subcmd});
}

V-ID/ms : 100 {
  if (readchan < NumCh) {
    sendCommand(readchan + 1, 0xcc, 0x00);
  }
  readchan += 1;
  readchan = readchan % 25;
}

V-ID/RS485 {
  u8 position;
  u8 realpos;
  u8 subid;
  u8 i;
  u8 chlow, chhigh;

  if (opt(0) == 0xd8 && opt(1) == ID && opt(optl - 1) == 255) {
    for (i = 1; i <= NumCh; ++i) {
      chlow = (1 << (i - 1)) & 0xff;
      chhigh = (1 << (i - 1)) >> 8 & 0xff;

      if (chlow == opt(2) && chhigh == opt(3)) {
        subid = 100 + i;
        realpos = opt(7);
        if (realpos < 0) {
          position = 0;
        } else if (realpos > 100) {
          position = 250;
        } else {
          position = (250 * (opt(7) - 0)) / (100 - 0);
        }
        setStatus(BLINDS:@subid, {0x41, position});
      }
    }
  }
}

V-ID/BLINDS:101 {
  u8 ch = 1;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:102 {
  u8 ch = 2;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:103 {
  u8 ch = 3;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:104 {
  u8 ch = 4;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:105 {
  u8 ch = 5;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:106 {
  u8 ch = 6;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:107 {
  u8 ch = 7;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:108 {
  u8 ch = 8;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:109 {
  u8 ch = 9;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:110 {
  u8 ch = 10;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:111 {
  u8 ch = 11;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:112 {
  u8 ch = 12;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:113 {
  u8 ch = 13;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:114 {
  u8 ch = 14;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:115 {
  u8 ch = 15;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}

V-ID/BLINDS:116 {
  u8 ch = 16;
  if (optl == 3) {

    if ((opt(0) & 7) == 2) {
      sendCommand(ch, 0x0a, 0xEE);
    }
    if ((opt(0) & 7) == 3) {
      sendCommand(ch, 0x0a, 0xDD);
    }
    if ((opt(0) & 7) == 4) {
      sendCommand(ch, 0x0a, 0xCC);
    }
  }
}