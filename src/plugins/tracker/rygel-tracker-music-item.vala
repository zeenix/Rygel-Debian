/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 * Copyright (C) 2008 Nokia Corporation, all rights reserved.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

using Rygel;
using GUPnP;
using DBus;

/**
 * Represents Tracker music item.
 */
public class Rygel.TrackerMusicItem : TrackerItem {
    private enum Metadata {
        FILE_NAME,
        MIME,
        SIZE,
        DURATION,
        TITLE,
        ARTIST,
        TRACK_NUM,
        ALBUM,
        RELEASE,
        DATE_ADDED,
        DATE,
        LAST_KEY
    }

    public TrackerMusicItem (string          id,
                             string          path,
                             TrackerCategory parent,
                             string[]        metadata) {
        base (id, path, parent, metadata);
    }

    public static string[] get_metadata_keys () {
        string[] keys = new string[Metadata.LAST_KEY];
        keys[Metadata.FILE_NAME] = "File:Name";
        keys[Metadata.MIME] = "File:Mime";
        keys[Metadata.SIZE] = "File:Size";
        keys[Metadata.DURATION] = "Audio:Duration";
        keys[Metadata.TITLE] = "Audio:Title";
        keys[Metadata.ARTIST] = "Audio:Artist";
        keys[Metadata.TRACK_NUM] = "Audio:TrackNo";
        keys[Metadata.ALBUM] = "Audio:Album";
        keys[Metadata.RELEASE] = "Audio:ReleaseDate";
        keys[Metadata.DATE_ADDED] = "Audio:DateAdded";
        keys[Metadata.DATE] = "DC:Date";

        return keys;
    }

    protected override void init_from_metadata (string[] values) {
        if (values[Metadata.TITLE] != "")
            this.title = values[Metadata.TITLE];
        else
            /* If title wasn't provided, use filename instead */
            this.title = values[Metadata.FILE_NAME];

        if (values[Metadata.SIZE] != "")
            this.size = values[Metadata.SIZE].to_int ();

        if (values[Metadata.DURATION] != "")
            this.duration = values[Metadata.DURATION].to_int ();

        if (values[Metadata.TRACK_NUM] != "")
            this.track_number = values[Metadata.TRACK_NUM].to_int ();

        if (values[Metadata.DATE] != "") {
            this.date = seconds_to_iso8601 (values[Metadata.DATE]);
        } else if (values[Metadata.RELEASE] != "") {
            this.date = seconds_to_iso8601 (values[Metadata.RELEASE]);
        } else {
            this.date = seconds_to_iso8601 (values[Metadata.DATE_ADDED]);
        }

        this.mime_type = values[Metadata.MIME];
        this.author = values[Metadata.ARTIST];
        this.album = values[Metadata.ALBUM];
        this.uris.add (Filename.to_uri (path, null));
    }
}

