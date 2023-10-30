from PyQt5.QtCore import QCommandLineParser, QCommandLineOption

#
NO_GROUP = "no-group"
NO_ONOFF = "no-onoff"
NO_LEVEL = "no-level"
NO_COLOR = "no-color"
NO_SCENE = "no-scene"
NO_OTA = "no-ota"
NO_AF = "no-af"
NO_HCI_OTA = "no-hci-ota"
NO_ANALYZE = "no-analyze"

GROUP = "group"
ONOFF = "onoff"
LEVEL = "level"
COLOR = "color"
SCENE = "scene"
OTA = "ota"
AF = "af"
HCI_OTA = "hci_ota"
ANALYZE = "analyze"
OPT_LINK_KEYS = "link-keys"
OPT_LOCAL_NETWORK = "local-network"
LINK_KEYS = "link_keys"
LOCAL_NETWORK = "local_network"
PRICE = "price"

# This option results in the options above all being enabled.
CLOUDSMETS = "cloudsmets"

class ZgcOptions:
    def __init__(self, app):
                    # Parse arguments here and remove/add tabs that we don't/do want.
        # The manner in which this done is:
        # - Tabs in the orignal code are defaulted present until removed
        # - New tabs can be explicitly added.
        parser = QCommandLineParser()
        parser.setApplicationDescription("Description")
        parser.addHelpOption()
        groupDisabled = QCommandLineOption(NO_GROUP, "Disable Group support")
        parser.addOption(groupDisabled)
        onOffDisabled = QCommandLineOption(NO_ONOFF, "Disable OnOff support")
        parser.addOption(onOffDisabled)
        levelDisabled = QCommandLineOption(NO_LEVEL, "Disable Level support")
        parser.addOption(levelDisabled)
        colorDisabled = QCommandLineOption(NO_COLOR, "Disable Color support")
        parser.addOption(colorDisabled)
        sceneDisabled = QCommandLineOption(NO_SCENE, "Disable Scene support")
        parser.addOption(sceneDisabled)
        otaDisabled = QCommandLineOption(NO_OTA, "Disable OTA support")
        parser.addOption(otaDisabled)
        afDisabled = QCommandLineOption(NO_AF, "Disable AF support")
        parser.addOption(afDisabled)
        hciOtaDisabled = QCommandLineOption(NO_HCI_OTA, "Disable HCI OTA support")
        parser.addOption(hciOtaDisabled)
        analysisDisabled = QCommandLineOption(NO_ANALYZE, "Disable Network Analysis support")
        parser.addOption(analysisDisabled)
        linkKeysEnabled = QCommandLineOption(OPT_LINK_KEYS, "Enable get link key")
        parser.addOption(linkKeysEnabled)
        localNetworkEnabled = QCommandLineOption(OPT_LOCAL_NETWORK, "Enable local network request")
        parser.addOption(localNetworkEnabled)
        priceEnabled = QCommandLineOption(PRICE, "Enable SE Price support")
        parser.addOption(priceEnabled)
        parser.process(app)

        # Now set attributes depending on what options are set.
        # Set the "no-<options>"
        setattr(self, GROUP, False if parser.isSet(NO_GROUP) else True)
        setattr(self, ONOFF, False if parser.isSet(NO_ONOFF) else True)
        setattr(self, LEVEL, False if parser.isSet(NO_LEVEL) else True)
        setattr(self, COLOR, False if parser.isSet(NO_COLOR) else True)
        setattr(self, SCENE, False if parser.isSet(NO_SCENE) else True)
        setattr(self, OTA, False if parser.isSet(NO_OTA) else True)
        setattr(self, AF, False if parser.isSet(NO_AF) else True)
        setattr(self, HCI_OTA, False if parser.isSet(NO_HCI_OTA) else True)
        setattr(self, ANALYZE, False if parser.isSet(NO_ANALYZE) else True)

        # Set the "<options>"
        setattr(self, LINK_KEYS, True if parser.isSet(OPT_LINK_KEYS) else False)
        setattr(self, LOCAL_NETWORK, True if parser.isSet(OPT_LOCAL_NETWORK) else False)
        setattr(self, PRICE, True if parser.isSet(PRICE) else False)
