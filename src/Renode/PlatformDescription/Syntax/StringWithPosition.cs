﻿//
// Copyright (c) Antmicro
//
// This file is part of the Renode project.
// Full license details are defined in the 'LICENSE' file.
//
using System;
using System.Collections.Generic;
using System.Linq;
using Sprache;

namespace Antmicro.Renode.PlatformDescription.Syntax
{
    public class StringWithPosition : IPositionAware<StringWithPosition>, IWithPosition, IVisitable
    {
        public StringWithPosition(string value)
        {
            Value = value;
        }

        public StringWithPosition SetPos(Position startPos, int length)
        {
            var result = new StringWithPosition(Value);
            result.Length = length;
            result.StartPosition = startPos;
            return result;
        }

        public override string ToString()
        {
            return Value;
        }

        public IEnumerable<object> Visit()
        {
            return Enumerable.Empty<object>();
        }

        public int Length { get; private set; }

        public Position StartPosition { get; private set; }

        public string Value { get; private set; }

        public static implicit operator string(StringWithPosition value)
        {
            return value.Value;
        }
    }
}
