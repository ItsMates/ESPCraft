package net.minecraft.server;

import java.io.IOException;
import java.util.UUID;

public class PacketPlayOutBoss implements Packet<PacketListenerPlayOut> {

    private UUID a;
    private PacketPlayOutBoss.Action b;
    private IChatBaseComponent c;
    private float d;
    private BossBattle.BarColor e;
    private BossBattle.BarStyle f;
    private boolean g;
    private boolean h;
    private boolean i;

    public PacketPlayOutBoss() {}

    public PacketPlayOutBoss(PacketPlayOutBoss.Action packetplayoutboss_action, BossBattle bossbattle) {
        this.b = packetplayoutboss_action;
        this.a = bossbattle.d();
        this.c = bossbattle.e();
        this.d = bossbattle.getProgress();
        this.e = bossbattle.g();
        this.f = bossbattle.h();
        this.g = bossbattle.i();
        this.h = bossbattle.j();
        this.i = bossbattle.k();
    }

    public void a(PacketDataSerializer packetdataserializer) throws IOException {
        this.a = packetdataserializer.i();
        this.b = (PacketPlayOutBoss.Action) packetdataserializer.a(PacketPlayOutBoss.Action.class);
        switch (this.b) {
        case ADD:
            this.c = packetdataserializer.f();
            this.d = packetdataserializer.readFloat();
            this.e = (BossBattle.BarColor) packetdataserializer.a(BossBattle.BarColor.class);
            this.f = (BossBattle.BarStyle) packetdataserializer.a(BossBattle.BarStyle.class);
            this.a(packetdataserializer.readUnsignedByte());

        case REMOVE:
        default:
            break;

        case UPDATE_PCT:
            this.d = packetdataserializer.readFloat();
            break;

        case UPDATE_NAME:
            this.c = packetdataserializer.f();
            break;

        case UPDATE_STYLE:
            this.e = (BossBattle.BarColor) packetdataserializer.a(BossBattle.BarColor.class);
            this.f = (BossBattle.BarStyle) packetdataserializer.a(BossBattle.BarStyle.class);
            break;

        case UPDATE_PROPERTIES:
            this.a(packetdataserializer.readUnsignedByte());
        }

    }

    private void a(int i) {
        this.g = (i & 1) > 0;
        this.h = (i & 2) > 0;
        this.i = (i & 2) > 0;
    }

    public void b(PacketDataSerializer packetdataserializer) throws IOException {
        packetdataserializer.a(this.a);
        packetdataserializer.a((Enum) this.b);
        switch (this.b) {
        case ADD:
            packetdataserializer.a(this.c);
            packetdataserializer.writeFloat(this.d);
            packetdataserializer.a((Enum) this.e);
            packetdataserializer.a((Enum) this.f);
            packetdataserializer.writeByte(this.j());

        case REMOVE:
        default:
            break;

        case UPDATE_PCT:
            packetdataserializer.writeFloat(this.d);
            break;

        case UPDATE_NAME:
            packetdataserializer.a(this.c);
            break;

        case UPDATE_STYLE:
            packetdataserializer.a((Enum) this.e);
            packetdataserializer.a((Enum) this.f);
            break;

        case UPDATE_PROPERTIES:
            packetdataserializer.writeByte(this.j());
        }

    }

    private int j() {
        int i = 0;

        if (this.g) {
            i |= 1;
        }

        if (this.h) {
            i |= 2;
        }

        if (this.i) {
            i |= 2;
        }

        return i;
    }

    public void a(PacketListenerPlayOut packetlistenerplayout) {
        packetlistenerplayout.a(this);
    }

    public static enum Action {

        ADD, REMOVE, UPDATE_PCT, UPDATE_NAME, UPDATE_STYLE, UPDATE_PROPERTIES;

        private Action() {}
    }
}