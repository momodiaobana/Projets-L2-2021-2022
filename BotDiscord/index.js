const discord = require('discord.js');
const momobot = new discord.Client({
    intents: [
        discord.Intents.FLAGS.GUILDS,
        discord.Intents.FLAGS.GUILD_MEMBERS,
        discord.Intents.FLAGS.GUILD_MESSAGES

    ]
});

const prefix = "!";
var injures = ["Putain", "Bordel", "Pétasse", "Catin", "Morue", "pute", "enculé", "connard", "connasse", "baise tes morts", "mange tes morts"];

momobot.on("ready", () => {
    console.log("en ligne");
})


momobot.on("guildMemberAdd", member => {
    member.guild.channels.cache.find(channel => channel.id === "904424918647709807").send(member.displayName + " Viens d'arriver!!  https://tenor.com/view/dance-emoji-meme-smiley-happy-dance-gif-16088006\n\n Nous sommes desormais : " + member.guild.memberCount);
    member.roles.add("904918892047134730");
});

momobot.on("guildMemberRemove", member => {
    member.guild.channels.cache.find(channel => channel.id === "904424918647709807").send(member.displayName + " Viens de nous quitter!!  https://tenor.com/view/dance-emoji-meme-smiley-happy-dance-gif-16088006\n\n Nous sommes desormais : " + member.guild.memberCount);
});

momobot.on("messageCreate", message => {
    if (message.author.bot) return;
    if (message.content === prefix + "ping") {
        message.setDescription("pong");
        message.reply("pong!");
    } else if (message.content === prefix + "help") {
        message.channel.send("Commande pas encore dispo!");

    }
});

momobot.on("messageCreate", message => {
    if (message.author.bot) return;
    for (var i = 0; i < injures.length; i++) {
        if (message.content === injures[i]) {
            message.delete();
            message.channel.send("**BELEK tu vas te faire mute zebi! OE c'est la dictature ma gueule !**\n" + "https://www.youtube.com/watch?v=hkWGQJM2QZI");
        }
    }
});

momobot.login("OTA0NDUxMzM3MjM5MDM1OTk2.YX7t8g.qUMLFdeRPzwqDJhWP-FmhOo4vIA");